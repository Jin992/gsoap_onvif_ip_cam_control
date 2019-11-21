/*
	chrono_duration.cpp

	See chrono_duration.h for documentation.

	Compile this file and link it with your code.

gSOAP XML Web services tools
Copyright (C) 2000-2015, Robert van Engelen, Genivia Inc., All Rights Reserved.
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
Copyright (C) 2000-2015, Robert van Engelen, Genivia, Inc., All Rights Reserved.
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

/* include soapH.h generated by soapcpp2 from .h file containing #import "chrono_duration.h" */
#ifdef SOAP_H_FILE      /* if set, use the soapcpp2-generated fileH.h file as specified with: cc ... -DSOAP_H_FILE=fileH.h */
# include "stdsoap2.h"
# include SOAP_XSTRINGIFY(SOAP_H_FILE)
#else
# include "Onvif/soapH.h"    /* or manually replace with soapcpp2-generated *H.h file */
#endif

static void * instantiate_xsd__duration(struct soap*, int, const char*, const char*, size_t*);

static int delete_xsd__duration(struct soap *soap, struct soap_clist*);

static void copy_xsd__duration(struct soap*, int, int, void*, size_t, const void*, void**);

SOAP_FMAC3 void SOAP_FMAC4 soap_default_xsd__duration(struct soap *soap, std::chrono::nanoseconds *a)
{
  (void)soap; /* appease -Wall -Werror */
  *a = a->zero();
}

SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_xsd__duration(struct soap *soap, const std::chrono::nanoseconds *a)
{
  (void)soap; (void)a; /* appease -Wall -Werror */
}

SOAP_FMAC3 const char * SOAP_FMAC4 soap_xsd__duration2s(struct soap *soap, std::chrono::nanoseconds a)
{
  LONG64 n = a.count();
  int k, h, m, s, f;
  if (n < 0)
  {
    soap_strcpy(soap->tmpbuf, sizeof(soap->tmpbuf), "-P");
    k = 2;
    n = -n;
  }
  else
  {
    soap_strcpy(soap->tmpbuf, sizeof(soap->tmpbuf), "P");
    k = 1;
  }
  f = n % 1000000000LL;
  n /= 1000000000LL;
  s = n % 60;
  n /= 60;
  m = n % 60;
  n /= 60;
  h = n % 24;
  n /= 24;
  if (n)
    (SOAP_SNPRINTF(soap->tmpbuf + k, sizeof(soap->tmpbuf) - k, 21), SOAP_LONG_FORMAT "D", n);
  if (h || m || s || f)
  {
    if (n)
      k = strlen(soap->tmpbuf);
    if (f)
      (SOAP_SNPRINTF(soap->tmpbuf + k, sizeof(soap->tmpbuf) - k, 14), "T%02dH%02dM%02d.%09dS", h, m, s, f);
    else
      (SOAP_SNPRINTF(soap->tmpbuf + k, sizeof(soap->tmpbuf) - k, 10), "T%02dH%02dM%02dS", h, m, s);
  }
  else if (!n)
    soap_strcpy(soap->tmpbuf + k, sizeof(soap->tmpbuf) - k, "T0S");
  return soap->tmpbuf;
}

SOAP_FMAC3 int SOAP_FMAC4 soap_out_xsd__duration(struct soap *soap, const char *tag, int id, const std::chrono::nanoseconds *a, const char *type)
{
  if (soap_element_begin_out(soap, tag, soap_embedded_id(soap, id, a, SOAP_TYPE_xsd__duration), type)
   || soap_string_out(soap, soap_xsd__duration2s(soap, *a), 0))
    return soap->error;
  return soap_element_end_out(soap, tag);
}

SOAP_FMAC3 int SOAP_FMAC4 soap_s2xsd__duration(struct soap *soap, const char *s, std::chrono::nanoseconds *a)
{
  LONG64 sign = 1, Y = 0, M = 0, D = 0, H = 0, N = 0, S = 0;
  double f = 0;
  *a = a->zero();
  if (s)
  {
    if (*s == '-')
    {
      sign = -1;
      s++;
    }
    if (*s != 'P' && *s != 'p')
      return soap->error = SOAP_TYPE;
    s++;
    /* date part */
    while (s && *s)
    {
      char *r = NULL;
      LONG64 n;
      if (*s == 'T' || *s == 't')
      {
	s++;
	break;
      }
      n = soap_strtol(s, &r, 10);
      if (!r)
	return soap->error = SOAP_TYPE;
      s = r;
      switch (*s)
      {
	case 'Y':
        case 'y':
	  Y = n;
	  break;
	case 'M':
	case 'm':
	  M = n;
	  break;
	case 'D':
	case 'd':
	  D = n;
	  break;
	default:
	  return soap->error = SOAP_TYPE;
      }
      s++;
    }
    /* time part */
    while (s && *s)
    {
      char *r = NULL;
      LONG64 n;
      n = soap_strtol(s, &r, 10);
      if (!r)
	return soap->error = SOAP_TYPE;
      s = r;
      switch (*s)
      {
	case 'H':
        case 'h':
	  H = n;
	  break;
	case 'M':
	case 'm':
	  N = n;
	  break;
	case '.':
	  S = n;
#if defined(WITH_C_LOCALE) && defined(HAVE_STRTOD_L)
# ifdef WIN32
          f = _strtod_l(s, NULL, SOAP_LOCALE(soap));
# else
          f = strtod_l(s, NULL, SOAP_LOCALE(soap));
# endif
#elif defined(HAVE_STRTOD)
          f = strtod(s, NULL);
#elif defined(WITH_C_LOCALE) && defined(HAVE_STRTOF_L)
          f = (double)strtof_l((char*)s, NULL, SOAP_LOCALE(soap));
#elif defined(HAVE_STRTOF)
          f = (double)strtof((char*)s, NULL);
#endif
	  s = NULL;
	  continue;
	case 'S':
	case 's':
	  S = n;
	  break;
	default:
	  return soap->error = SOAP_TYPE;
      }
      s++;
    }
    /* convert Y-M-D H:N:S.f to std::chrono::nanoseconds */
    std::chrono::hours hours(sign * ((((((Y * 12) + M) * 30) + D) * 24) + H));
    std::chrono::seconds seconds(sign * ((N * 60) + S));
    std::chrono::nanoseconds nanos(sign * (LONG64)(1e9 * f + 0.5));
    *a = hours + seconds + nanos;
  }
  return soap->error;
}

SOAP_FMAC3 std::chrono::nanoseconds * SOAP_FMAC4 soap_in_xsd__duration(struct soap *soap, const char *tag, std::chrono::nanoseconds *a, const char *type)
{
  if (soap_element_begin_in(soap, tag, 0, NULL))
    return NULL;
  if (*soap->type
   && soap_match_tag(soap, soap->type, type)
   && soap_match_tag(soap, soap->type, ":duration"))
  {
    soap->error = SOAP_TYPE;
    soap_revert(soap);
    return NULL;
  }
  a = (std::chrono::nanoseconds*)soap_id_enter(soap, soap->id, a, SOAP_TYPE_xsd__duration, sizeof(std::chrono::nanoseconds), NULL, NULL, instantiate_xsd__duration, NULL);
  if (*soap->href)
    a = (std::chrono::nanoseconds*)soap_id_forward(soap, soap->href, a, 0, SOAP_TYPE_xsd__duration, 0, sizeof(std::chrono::nanoseconds), 0, copy_xsd__duration, NULL);
  else if (a)
  {
    if (soap_s2xsd__duration(soap, soap_value(soap), a))
      return NULL;
  }
  if (soap->body && soap_element_end_in(soap, tag))
    return NULL;
  return a;
}

static void * instantiate_xsd__duration(struct soap *soap, int n, const char *type, const char *arrayType, size_t *size)
{
  DBGLOG(TEST, SOAP_MESSAGE(fdebug, "soap_instantiate_xsd__duration(%d, %s, %s)\n", n, type?type:"", arrayType?arrayType:""));
  struct soap_clist *cp = soap_link(soap, SOAP_TYPE_xsd__duration, n, delete_xsd__duration);
  (void)type; (void)arrayType; /* appease -Wall -Werror */
  if (!cp)
    return NULL;
  if (n < 0)
  {	cp->ptr = SOAP_NEW(soap, std::chrono::nanoseconds);
    if (size)
      *size = sizeof(std::chrono::nanoseconds);
  }
  else
  {	cp->ptr = SOAP_NEW_ARRAY(soap, std::chrono::nanoseconds, n);
    if (size)
      *size = n * sizeof(std::chrono::nanoseconds);
  }
  DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Instantiated location=%p\n", cp->ptr));
  if (!cp->ptr)
    soap->error = SOAP_EOM;
  return (std::chrono::nanoseconds*)cp->ptr;
}

static int delete_xsd__duration(struct soap *soap, struct soap_clist *p)
{
  (void)soap; /* appease -Wall -Werror */
  if (p->type == SOAP_TYPE_xsd__duration)
  {
    if (p->size < 0)
      SOAP_DELETE(soap, static_cast<std::chrono::nanoseconds*>(p->ptr), std::chrono::nanoseconds);
    else
      SOAP_DELETE_ARRAY(soap, static_cast<std::chrono::nanoseconds*>(p->ptr), std::chrono::nanoseconds);
    return SOAP_OK;
  }
  return SOAP_ERR;
}

static void copy_xsd__duration(struct soap *soap, int st, int tt, void *p, size_t index, const void *q, void **x)
{
  (void)soap; (void)st; (void)tt; (void)index; (void)x; /* appease -Wall -Werror */
  DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Copying std::chrono::nanoseconds %p -> %p\n", q, p));
  *(std::chrono::nanoseconds*)p = *(std::chrono::nanoseconds*)q;
}
