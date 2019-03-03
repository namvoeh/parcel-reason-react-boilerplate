module type Config = {
  type route;

  let toUrl: route => string;
  let toRoute: ReasonReact.Router.url => route;
};

module Config = {
  type route =
    | Home
    | RandomDog
    | NotFound;

  let toRoute = (url: ReasonReact.Router.url) =>
    switch (url.path) {
    | [""]
    | []
    | ["/"] => Home
    | ["random-me-a-dog"] => RandomDog
    | _ => NotFound
    };

  let toUrl =
    fun
    | Home => "/"
    | RandomDog => "/random-me-a-dog"
    | NotFound => "/404";
};

module Link = {
  let component = ReasonReact.statelessComponent("Link");
  let make = (~route, children) => {
    ...component,
    render: _self => {
      let href = Config.toUrl(route);
      let onClick = e => {
        ReactEvent.Mouse.preventDefault(e);
        ReasonReact.Router.push(href);
      };
      <a href onClick> {children |> ReasonReact.array} </a>;
    },
  };
};
