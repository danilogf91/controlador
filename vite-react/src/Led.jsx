import { useState } from "react";
import "./App.css";

function Led({ name }) {
  const [count, setCount] = useState(false);

  return (
    <div className="card">
      <h3>{name}</h3>
      <button onClick={() => setCount((count) => !count)}>
        {name} {count ? "ON" : "OFF"}
      </button>
    </div>
  );
}

export default Led;
