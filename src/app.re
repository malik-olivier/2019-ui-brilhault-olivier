type page = 
    | Dashboard
    | Login;

module App = {
    type state = {route: page};
    type action =
        | UpdatePage(page);
    let component = ReasonReact.reducerComponent("App");
    let make = _children => {
        ...component, 
        initialState: () => {route: Dashboard},
        didMount: self => {
            let watcherID =
              ReasonReact.Router.watchUrl(url =>
                switch (url.path) {
                | ["login"] => self.send(UpdatePage(Login))
                | _ => self.send(UpdatePage(Dashboard))
                }
              );
              self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
          },
        reducer: (action, _state) =>
            switch (action) {
            | UpdatePage(route) => ReasonReact.Update({route: route})
            },
        
        render: ({state}) =>
        <div>(
          switch (state.route) {
          | Dashboard => <Register />
          | Login => <Login />
          }
        )</div>
    };
  };

  ReactDOMRe.renderToElementWithId(<App />, "main");
