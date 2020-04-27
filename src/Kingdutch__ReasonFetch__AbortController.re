type signal;
type t = {
  signal: signal
};

[@bs.new]
external make : unit => t = "AbortController";

[@bs.send]
external abort : t => unit = "abort";
