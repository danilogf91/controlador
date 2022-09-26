import React from "react";
import ReactDOM from "react-dom/client";
import Led from "./Led";
import "./index.css";
import Title from "./Title";

ReactDOM.createRoot(document.getElementById("root")).render(
  <React.StrictMode>
    <Title title="Control Principal" />
    <Led name="LED 1" />
    <Led name="LED 2" />
  </React.StrictMode>
);
