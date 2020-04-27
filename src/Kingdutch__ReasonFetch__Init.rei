type t;

type headers;
type bodyInit;
type signal;

let make: (
  ~_method :        string=?,
  ~headers :        headers=?,
  ~body :           bodyInit=?,
  ~referrer :       string=?,
  ~referrerPolicy : string=?,
  ~mode :           string=?,
  ~credentials :    string=?,
  ~cache :          string=?,
  ~redirect :       string=?,
  ~integrity :      string=?,
  ~keepalive :      bool=?,
  ~signal :         signal=?,
  unit
) => t;
