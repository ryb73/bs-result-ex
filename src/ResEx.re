open Belt.Result;

let ok = v => Ok(v);
let error = v => Error(v);

let get = fun
    | Ok(v) => Some(v)
    | Error(_) => None;

let fromOpt = (error) => fun
    | None => Error(error)
    | Some(v) => Ok(v);

let getError = fun
    | Error(e) => Some(e)
    | Ok(_) => None;

let bindError = (callback) => fun
    | Ok(v) => Ok(v)
    | Error(e) => callback(e);

let mapError = (callback) => bindError(e => Error(callback(e)));

let raiseExn = (payload) => {
    Js.Promise.resolve(payload) |> ignore;
    let err = [%bs.raw {| new Error("ResEx.getExn") |}];
    Js.Dict.set(err, "payload", payload);
    raise(err);
};

let getExn = fun
    | Ok(v) => v
    | Error(payload) => raiseExn(payload);

let rec elevateArrayHelper = (index, array, result) =>
    switch (result, index, Js.Array.length(array)) {
        | (Ok(newArr), i, l) when i < l =>
            switch (array[index]) {
                | Ok(v) => {
                    Js.Array.push(v, newArr) |> ignore;
                    elevateArrayHelper(index + 1, array, result);
                }
                | Error(_) as error => error
            }

        | (Ok(_), _, _)
        | (Error(_), _, _) => result
    };

let elevateArray = (array) =>
    elevateArrayHelper(0, array, Ok([||]));
