let ok: 'a => Belt.Result.t('a, 'b);
let error: 'a => Belt.Result.t('b, 'a);
let toOpt: Belt.Result.t('a, 'b) => option('a);
let fromOpt: ('a, option('b)) => Belt.Result.t('b, 'a);
let getError: Belt.Result.t('a, 'b) => option('b);
let bindError:
    ('a => Belt.Result.t('b, 'c), Belt.Result.t('b, 'a))
    => Belt.Result.t('b, 'c);
let mapError: ('a => 'b, Belt.Result.t('c, 'a)) => Belt.Result.t('c, 'b);
let getExn: Belt.Result.t('a, 'b) => 'a;
let elevateArray: Js.Array.t(Belt.Result.t('a, 'b)) => Belt.Result.t(Js.Array.t('a), 'b);
