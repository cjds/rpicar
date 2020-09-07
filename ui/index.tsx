import React from "react";
import ReactDOM from "react-dom";
import { AppBar } from "./components/AppBar/AppBar";
import { Footer } from "./components/Footer/Footer";
import styles from "./index.css";

ReactDOM.render(
  <div className={styles.myapp}>
    <AppBar />
    <div className="body">
      <h1>Alloh1>
    </div>
    <Footer />
  </div>,
  document.querySelector("#root")
)
