type t =
  | Home
  | RandomDog
  | NotFound;

type route = t;

let routeToUrl =
  fun
  | Home => "/"
  | RandomDog => "/random-me-a-dog"
  | NotFound => "/404";

let urlToRoute: ReasonReact.Router.url => t =
  url =>
    switch (url.path) {
    | [""]
    | []
    | ["/"] => Home
    | ["random-me-a-dog"] => RandomDog
    | _ => NotFound
    };
