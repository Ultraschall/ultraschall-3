/*
** JNetLib
** Copyright (C) 2008 Cockos Inc
** Copyright (C) 2003 Nullsoft, Inc.
** Author: Justin Frankel
** File: webserver.h - Generic simple webserver baseclass
** License: see jnetlib.h
**
** You can derive your object from WebServerBaseClass to do simple web serving. Example:

  class wwwServer : public WebServerBaseClass
  {
  public:
    wwwServer() { } 
    virtual IPageGenerator *onConnection(JNL_HTTPServ *serv, int port)
    {
      serv->set_reply_header("Server:jnetlib_test/0.0");
      if (!strcmp(serv->get_request_file(),"/"))
      {
        serv->set_reply_string("HTTP/1.1 200 OK");
        serv->set_reply_header("Content-Type:text/html");
        serv->send_reply();

        return new MemPageGenerator(strdup("Test Web Server v0.0"));
      }
      else
      {
        serv->set_reply_string("HTTP/1.1 404 NOT FOUND");
        serv->send_reply();
        return 0; // no data
      }
    }
  };


    wwwServer foo;
    foo.addListenPort(8080);
    while (1)
    {
      foo.run();
      Sleep(10);
    }

  You will also need to derive from the IPageGenerator interface to provide a data stream, here is an
  example of MemPageGenerator:

    class MemPageGenerator : public IPageGenerator
    {
      public:
        virtual ~MemPageGenerator() { free(m_buf); }
        MemPageGenerator(char *buf, int buf_len=-1) { m_buf=buf; if (buf_len >= 0) m_buf_size=buf_len; else m_buf_size=strlen(buf); m_buf_pos=0; }
        virtual int GetData(char *buf, int size) // return 0 when done
        {
          int a=m_buf_size-m_buf_pos;
          if (a < size) size=a;
          memcpy(buf,m_buf+m_buf_pos,size);
          m_buf_pos+=size;
          return size;
        }

      private:
        char *m_buf;
        int m_buf_size;
        int m_buf_pos;
    };


**
*/


#ifndef _JNL_WEBSERVER_H_
#define _JNL_WEBSERVER_H_

#include "httpserv.h"

class IPageGenerator
{
public:
  virtual ~IPageGenerator() { };
  virtual int IsNonBlocking() { return 0; } // override this and return 1 if GetData should be allowed to return 0
  virtual int GetData(char *buf, int size)=0; // return < 0 when done (or 0 if IsNonBlocking() is 1)
};



class WS_ItemList;
class WS_conInst;

class WebServerBaseClass
{
protected: // never create one of these directly, always derive
  WebServerBaseClass();

public:
  virtual ~WebServerBaseClass();

  // stuff for setting limits/timeouts
  void setMaxConnections(int max_con);
  void setRequestTimeout(int timeout_s);

  // stuff for setting listener port
  int addListenPort(int port, unsigned long which_interface=0);
  int getListenPort(int idx, int *err=0);
  void removeListenPort(int port);
  void removeListenIdx(int idx);

  // call this a lot :)
  void run(void);

  // if you want to manually attach a connection, use this:
  // you need to specify the port it came in on so the web server can build
  // links
  void attachConnection(JNL_IConnection *con, int port);

  // derived classes need to override this one =)
  virtual IPageGenerator *onConnection(JNL_HTTPServ *serv, int port)=0;

  // stats getting functions

  // these can be used externally, as well as are used by the web server
  static void url_encode(char *in, char *out, int max_out);
  static void url_decode(char *in, char *out, int maxlen);
  static void base64decode(char *src, char *dest, int destsize);
  static void base64encode(char *in, char *out);

  static int parseAuth(char *auth_header, char *out, int out_len);//returns 0 on unknown auth, 1 on basic


private:
  int run_connection(WS_conInst *con);

  int m_timeout_s;
  int m_max_con;

  JNL_AsyncDNS m_dns;

  WS_ItemList *m_listeners;
  int m_listener_rot;
  WS_ItemList *m_connections;
};

#endif//_JNL_WEBSERVER_H_