open Js.Result;

let toOpt = fun
    | Ok(v) => Some(v)
    | _ => None;

let getError = fun
    | Error(e) => Some(e)
    | _ => None;

let bind = (callback) => fun
    | Ok(v) => callback(v)
    | Error(e) => Error(e);

let map = (callback) => bind(v => Ok(callback(v)));

let bindError = (callback) => fun
    | Ok(v) => Ok(v)
    | Error(e) => callback(e);

let mapError = (callback) => bindError(e => Error(callback(e)));
