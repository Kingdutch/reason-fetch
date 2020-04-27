type t;

type headers;
type bodyInit;

[@bs.obj]
external make : (
  ~_method:        string=?,
  ~headers:        headers=?,
  ~body:           bodyInit=?,
  ~referrer:       string=?,
  ~referrerPolicy: string=?,
  ~mode:           string=?,
  ~credentials:    string=?,
  ~cache:          string=?,
  ~redirect:       string=?,
  ~integrity:      string=?,
  ~keepalive:      bool=?,
  ~signal:         Kingdutch__ReasonFetch__AbortController.signal=?,
  unit
) => t = "";

let make = (
  ~_method = ?,
  ~headers = ?,
  ~body = ?,
  ~referrer = ?,
  ~referrerPolicy = ?,
  ~mode = ?,
  ~credentials = ?,
  ~cache = ?,
  ~redirect = ?,
  ~integrity = ?,
  ~keepalive = ?,
  ~signal = ?,
  ()
) => make(
  ~_method?,
  ~headers?,
  ~body?,
  ~referrer?,
  ~referrerPolicy?,
  ~mode?,
  ~credentials?,
  ~cache?,
  ~redirect?,
  ~integrity?,
  ~keepalive?,
  ~signal?,
  ()
);