// Tell users they should open the console for the output.
[@bs.scope "document"] [@bs.val]
external documentWrite : string => unit = "write"
documentWrite("Open the console for output.");

// A simple result printer to convert an `option` to a console message.
let result_printer = message => result => switch (result) {
  | Ok(s) => { Js.log2(message, "ok"); Js.log(s); }
  | Error(`FetchError(s)) => { Js.log2(message, "fetch error"); Js.log(s); }
  | Error(`FetchAborted) => { Js.log2(message, "fetch aborted"); }
};

open Kingdutch__ReasonFetch;
module AbortController = Kingdutch__ReasonFetch__AbortController;
module Init = Kingdutch__ReasonFetch__Init;

// Successful request
fetch("https://httpbin.org/get")
->Promise.get(result_printer("/get"));

// Fetch 404 error code
fetch("https://httpbin.org/status/404")
->Promise.get(result_printer("/status/404"));

// Fetch nonexistent service
fetch("http://localhost:9001")
->Promise.get(result_printer("localhost:9001"));

// Fetch POST with some data
fetch("https://httpbin.org/post", ~init=Init.t(~_method="POST", ()))
->Promise.get(result_printer("/post"));

// Trigger a CORS error.
fetch("https://httpbin.org/get", ~init=Init.t(~mode="same-origin", ()))
->Promise.get(result_printer("CORS Error /get"));

// Example of an aborted fetch.
let controller = AbortController.make();
fetch("http://httpbin.org/bytes/1024", ~init=Init.t(~signal=controller.signal, ()))
->Promise.get(result_printer("/bytes/1024"));
controller
  ->AbortController.abort;

// Example of a failed clone.
fetch("http://httpbin.org/json")
->Promise.get(result => {
  switch (result) {
    | Ok(response) => {
      response
        ->Kingdutch__ReasonFetch__Response.json
        ->Promise.get(jsonR => {
          Js.log("/json");
          switch (jsonR) {
            | Ok(json) => Js.log(json)
            | Error(`ResponseBodyRead(e)) => Js.log2("ResposeBodyRead", e)
            | Error(`JsonParseError(e)) => Js.log2("JsonParseError", e)
            | Error(`UnknownError(e)) => Js.log2("UnknownError", e)
          }
        }
      )
    }
    | Error(_) => Js.log("Unexpected error in clone fail example")
  }
})
