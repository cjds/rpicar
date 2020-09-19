import React from "react";
import ReactDOM from "react-dom";
import {AppBar} from "./components/AppBar/AppBar";

ReactDOM.render(
  <div className="DD">
    <div className="body">
    <AppBar />
      <h1>Allo, </h1>
    </div>
  </div>,
  document.querySelector("#root")
);

