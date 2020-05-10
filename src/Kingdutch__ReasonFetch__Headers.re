type t;

// TODO: Some of these errors can cause read errors depending on various factors.

[@bs.new] external make: unit => t = "Headers";
[@bs.new] external makeFromObject: Js.t({..}) => t = "Headers";

[@bs.send] external append: (t, string, string) => unit = "append";
[@bs.send] external delete: (t, string) => unit = "delete";
[@bs.send] external entries: t => Js.t({..}) = "entries";
[@bs.send] external get: (t, string) => string = "get";
[@bs.send] external has: (t, string) => bool = "has";
[@bs.send] external set: (t, string, string) => unit = "set";
[@bs.send] external values: t => Js.t({..}) = "values";