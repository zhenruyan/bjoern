struct _Transaction {
    int client_fd;

    ev_io       read_watcher;
    size_t      read_seek;
    /* TODO: put request_* into a seperate data structure. */
    bjoern_http_parser* request_parser;

    const char* request_url;
    http_method request_method;
    PyObject*   wsgi_environ;

    /* Write stuff: */
    ev_io       write_watcher;
    size_t      response_remaining;
    PyObject*   response_file;
    PyObject*   response_status;
    PyObject*   response_headers;
    bool        headers_sent;
    const char* response;
    request_handler request_handler;
};

static Transaction* Transaction_new();
#define Transaction_free(t) Py_DECREF(t->wsgi_environ); \
                            Py_XDECREF(t->response_headers); \
                            Py_XDECREF(t->response_status); \
                            Py_XDECREF(t->response_file); \
                            free(t->request_parser); \
                            free(t)
