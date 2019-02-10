open Register;
open Login;

let str = ReasonReact.string;

module type Router = {let dangerouslyGetInitialUrl: unit => ReasonReact.Router.url;};

module App = {
  type page =
    | Login
    | Register;

  type state = {route: page};

  type action =
    | RedirectToLogin
    | RedirectToRegister;

  let component = ReasonReact.reducerComponent("App");

  let toPage = (url: ReasonReact.Router.url) =>
    switch (url.hash) {
    | "login" => Login
    | _ => Register
    };

  let toUrl = page =>
    switch (page) {
    | Login => "login"
    | _ => "register"
    };

  let make = _children => {
    ...component,
    initialState: () => {route: ReasonReact.Router.dangerouslyGetInitialUrl() |> toPage},
    reducer: (action, state) =>
      switch (action) {
      /* router actions */
      | RedirectToLogin => ReasonReact.Update({...state, route: Login})
      | RedirectToRegister => ReasonReact.Update({...state, route: Register})
      },
    didMount: self => {
      let watcherID =
        ReasonReact.Router.watchUrl(url =>
          switch (url.hash) {
          | "login" => self.send(RedirectToLogin)
          | "register" => self.send(RedirectToRegister)
          | _ => self.send(RedirectToRegister)
          }
        );
      self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
    },
    render: ({state}) =>
      <div>
        {switch (state.route) {
         | Login => <Login />
         | Register => <Register />
         }}
        <a href="login"> {str("Login")} </a>
        <a href="register"> {str("Register")} </a>
      </div>,
  };
};

//ReactDOMRe.renderToElementWithId(<App />, "main");
