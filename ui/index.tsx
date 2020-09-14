import React from "react";
import ReactDOM from "react-dom";
import { AppBar } from "./components/AppBar/AppBar";

ReactDOM.render(
  <div className="DD">
    <AppBar />
    <div className="body">
      <h1>Allo, </h1>
    </div>
  </div>,
  document.querySelector("#root")
);

