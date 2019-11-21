/*
        qdatetime.cpp

        See qdatetime.h for documentation.

        Compile this file and link it with your code.

gSOAP XML Web services tools
Copyright (C) 2000-2016, Robert van Engelen, Genivia Inc., All Rights Reserved.
This part of the software is released under ONE of the following licenses:
GPL, the gSOAP public license, OR Genivia's license for commercial use.
--------------------------------------------------------------------------------
gSOAP public license.

The contents of this file are subject to the gSOAP Public License Version 1.3
(the "License"); you may not use this file except in compliance with the
License. You may obtain a copy of the License at
http://www.cs.fsu.edu/~engelen/soaplicense.html
Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
for the specific language governing rights and limitations under the License.

The Initial Developer of the Original Code is Robert A. van Engelen.
Copyright (C) 2000-2016, Robert van Engelen, Genivia, Inc., All Rights Reserved.
--------------------------------------------------------------------------------
GPL license.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA

Author contact information:
engelen@genivia.com / engelen@acm.org

This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

/* When using soapcpp2 option -q<name> or -p<name>, you need to change "soapH.h" below */

/* include soapH.h generated by soapcpp2 from .h file containing #import "qdatetime.h" */
#ifdef SOAP_H_FILE      /* if set, use the soapcpp2-generated fileH.h file as specified with: cc ... -DSOAP_H_FILE=fileH.h */
# include "stdsoap2.h"
# include SOAP_XSTRINGIFY(SOAP_H_FILE)
#else
# include "Onvif/soapH.h"    /* or manually replace with soapcpp2-generated *H.h file */
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0)) && QT_CONFIG(timezone)
# include <QTimeZone>
#endif

static void * instantiate_xsd__dateTime(struct soap*, int, const char*, const char*, size_t*);

static int delete_xsd__dateTime(struct soap*, struct soap_clist*);

static void copy_xsd__dateTime(struct soap*, int, int, void*, size_t, const void*, void**);

void soap_serialize_xsd__dateTime(struct soap *soap, QDateTime const *a)
{
  (void)soap; (void)a; /* appease -Wall -Werror */
}

void soap_default_xsd__dateTime(struct soap *soap, QDateTime *a)
{
  (void)soap; /* appease -Wall -Werror */
  *a = QDateTime();
}

int soap_out_xsd__dateTime(struct soap *soap, char const *tag, int id, QDateTime const *a, char const *type)
{
  if (soap_element_begin_out(soap, tag, soap_embedded_id(soap, id, a, SOAP_TYPE_xsd__dateTime), type)
   || soap_string_out(soap, soap_xsd__dateTime2s(soap, *a), 0))
    return soap->error;
  return soap_element_end_out(soap, tag);
}

QDateTime *soap_in_xsd__dateTime(struct soap *soap, char const *tag, QDateTime *a, char const *type)
{
  if (soap_element_begin_in(soap, tag, 0, NULL))
    return NULL;
  if (*soap->type
   && soap_match_att(soap, soap->type, type)
   && soap_match_att(soap, soap->type, ":dateTime"))
  {
    soap->error = SOAP_TYPE;
    soap_revert(soap);
    return NULL;
  }
  a = (QDateTime*)soap_id_enter(soap, soap->id, a, SOAP_TYPE_xsd__dateTime, sizeof(QDateTime), NULL, NULL, instantiate_xsd__dateTime, NULL);
  if (*soap->href == '#')
  {
    a = (QDateTime*)soap_id_forward(soap, soap->href, a, 0, SOAP_TYPE_xsd__dateTime, 0, sizeof(QDateTime), 0, copy_xsd__dateTime, NULL);
  }
  else if (a)
  {
    if (soap_s2xsd__dateTime(soap, soap_value(soap), a))
      return NULL;
  }
  if (soap->body && soap_element_end_in(soap, tag))
    return NULL;
  return a;
}

const char * soap_xsd__dateTime2s(struct soap *soap, QDateTime a)
{
  /* YYYY-MM-DDThh:mm:ss.sssZ */
  if (!a.isValid())
    a = QDateTime(QDate(1, 1, 1), QTime(0, 0, 0), Qt::UTC);
  else
    a = a.toUTC();
#ifndef WITH_NOZONE
  QString str = a.toString(QStringLiteral("yyyy-MM-ddTHH:mm:ss.zzzZ"));
#else
  QString str = a.toString(QStringLiteral("yyyy-MM-ddTHH:mm:ss.zzz"));
#endif
  QByteArray ba = str.toLatin1();
  soap_strcpy(soap->tmpbuf, qstrlen(ba)+1, ba.constData());
  return soap->tmpbuf;
}

int soap_s2xsd__dateTime(struct soap *soap, const char *s, QDateTime *a)
{
  *a = QDateTime();
  a->setTimeSpec(Qt::UTC);
  if (s)
  {
    char *t;
    unsigned long d;
    int yr = 0, mon = 0, day = 0;
    d = soap_strtoul(s, &t, 10);
    if (*t == '-')
    {
      /* YYYY-MM-DD */
      yr = (int)d;
      mon = (int)soap_strtoul(t + 1, &t, 10);
      day = (int)soap_strtoul(t + 1, &t, 10);
    }
    else if (!(soap->mode & SOAP_XML_STRICT))
    {
      /* YYYYMMDD */
      yr = (int)(d / 10000);
      mon = (int)(d / 100 % 100);
      day = (int)(d % 100);
    }
    else
    {
      return soap->error = SOAP_TYPE;
    }
    //set the date
    a->setDate(QDate(yr, mon, day));
    //grab hrs, mins, secs, and mills
    int hrs = 0, mins = 0, secs = 0, mills = 0;
    if (*t == 'T' || ((*t == 't' || *t == ' ') && !(soap->mode & SOAP_XML_STRICT)))
    {
      d = soap_strtoul(t + 1, &t, 10);
      if (*t == ':')
      {
        /* Thh:mm:ss */
        hrs = d;
        mins = (int)soap_strtoul(t + 1, &t, 10);
        secs = (int)soap_strtoul(t + 1, &t, 10);
      }
      else if (!(soap->mode & SOAP_XML_STRICT))
      {
        /* Thhmmss */
        hrs = (int)(d / 10000);
        mins = (int)(d / 100 % 100);
        secs = (int)(d % 100);
      }
      else
      {
        return soap->error = SOAP_TYPE;
      }
    }
    //grab the milliseconds if it's included
    if (*t == '.')
      mills = (int)soap_strtoul(t+1, &t, 10);
    //set the time
    a->setTime(QTime(hrs, mins, secs, mills));
    //grab the timezone and adjust DateTime
    if (*t == ' ' && !(soap->mode & SOAP_XML_STRICT))
      t++;
    if (*t)
    {
#ifndef WITH_NOZONE
      if (*t == '+' || *t == '-')
      {
        int hrs, mins;
        mins = (int)soap_strtol(t, &t, 10);
        if (*t == ':')
        {
          /* +hh:mm */
          hrs = mins;
          mins = (int)soap_strtol(t + 1, &t, 10);
          if (hrs < 0)
            mins = -mins;
        }
        else if (!(soap->mode & SOAP_XML_STRICT))
        {
          /* +hhmm */
          hrs = mins / 100;
          mins = mins % 100;
        }
        else
        {
          /* +hh */
          hrs = mins;
          mins = 0;
        }
        if (*t)
          return soap->error = SOAP_TYPE;
        int offsetSeconds = mins*60 + hrs*3600;
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0)) && QT_CONFIG(timezone)
        a->setTimeZone(QTimeZone(offsetSeconds));
#else
        *a = a->addSecs(offsetSeconds);
#endif
      }
      else if (*t != 'Z')
        return soap->error = SOAP_TYPE;
#endif
    }
    else
    {
      /* no UTC or timezone, so assume we got a localtime */
    }
  }
  return soap->error;
}

static void * instantiate_xsd__dateTime(struct soap *soap, int n, const char *type, const char *arrayType, size_t *size)
{
  DBGLOG(TEST, SOAP_MESSAGE(fdebug, "soap_instantiate_xsd__dateTime(%d, %s, %s)\n", n, type?type:"", arrayType?arrayType:""));
  struct soap_clist *cp = soap_link(soap, SOAP_TYPE_xsd__dateTime, n, delete_xsd__dateTime);
  (void)type; (void)arrayType; /* appease -Wall -Werror */
  if (!cp)
    return NULL;
  if (n < 0)
  {	cp->ptr = SOAP_NEW(soap, QDateTime);
    if (size)
      *size = sizeof(QDateTime);
  }
  else
  {	cp->ptr = SOAP_NEW_ARRAY(soap, QDateTime, n);
    if (size)
      *size = n * sizeof(QDateTime);
  }
  DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Instantiated location=%p\n", cp->ptr));
  if (!cp->ptr)
    soap->error = SOAP_EOM;
  return (QDateTime*)cp->ptr;
}

static int delete_xsd__dateTime(struct soap *soap, struct soap_clist *p)
{
  (void)soap; /* appease -Wall -Werror */
  if (p->type == SOAP_TYPE_xsd__dateTime)
  {
    if (p->size < 0)
      SOAP_DELETE(soap, static_cast<QDateTime*>(p->ptr), QDateTime);
    else
      SOAP_DELETE_ARRAY(soap, static_cast<QDateTime*>(p->ptr), QDateTime);
    return SOAP_OK;
  }
  return SOAP_ERR;
}

static void copy_xsd__dateTime(struct soap *soap, int st, int tt, void *p, size_t index, const void *q, void **x)
{
  (void)soap; (void)st; (void)tt; (void)index; (void)x; /* appease -Wall -Werror */
  DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Copying QDateTime %p -> %p\n", q, p));
  *(QDateTime*)p = *(QDateTime*)q;
}
