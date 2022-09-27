import React, { useState, useEffect } from "react";
import createModule from "./module.mjs";

function useWebAssembly() {
  const [loading, setLoading] = useState(true);
  const [module, setModule] = useState();
  useEffect(
    () =>
      createModule().then((module) => {
        setModule(module);
        setLoading(false);
      }),
    []
  );
  return [module, loading];
}

const style = {
  textAlign: "center",
  margin: "1em",
  padding: "1em",
  backgroundColor: "#f8f8f8",
  border: "1px solid black",
  borderRadius: ".25em",
};

function App() {
  const [module, loading] = useWebAssembly();
  if (loading) return "WebAssembly is loading...";

  return (
    <div className="App">
      <div style={style}>
        {!loading ? module.HelloWorld("Aardhyn Lavender") : "Loading..."}
      </div>
    </div>
  );
}

export default App;
