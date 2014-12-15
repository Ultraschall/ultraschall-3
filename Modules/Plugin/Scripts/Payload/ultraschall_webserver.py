from reaper_python import *
from wsgiref.simple_server import make_server
from cgi import parse_qs, escape

def hello_reaper(environ, start_response):
    parameters = parse_qs(environ.get('QUERY_STRING', ''))
    if 'insert_track' in parameters:
        start_response('200 OK', [('Content-Type', 'text/html')])
        index = int(parameters['insert_track'][0])
        RPR_InsertTrackAtIndex(index, True)
        RPR_TrackList_AdjustWindows(True)
        return ["Track added at %s\n" % (index)]
    start_response('200 OK', [('Content-Type', 'text/html')])
    return [""]

# start a http server to run our wsgi app
httpd = make_server('', 8000, hello_reaper)
# tweak for best performance
httpd.timeout = 0.1

# deferred loop
def http_serve():
    httpd.handle_request()
    RPR_defer("http_serve()")

http_serve()