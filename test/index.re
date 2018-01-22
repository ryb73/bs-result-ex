open Js.Result;
open ResultEx;

let get = fun
    | Some x => x
    | None => failwith "error";

Ok "yeah"
    |> map @@ (^) " ok"
    |> toOpt
    |> get
    |> Js.log;

Error "oh"
    |> mapError @@ (^) " an error"
    |> getError
    |> Js.log;