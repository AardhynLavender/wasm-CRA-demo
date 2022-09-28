import React, { useState, useEffect } from "react";
import createModule from "./module.mjs";

function useWebAssembly() {
  const [loading, setLoading] = useState(true);
  const [module, setModule] = useState();
    useEffect(() => {
        createModule({ canvas: document.querySelector("#canvas") }).then((module) => {
            setModule(module);
            setLoading(false);
        });
    }, []);
  return [ module, loading];
}

const style = {
    textAlign: "center",
    margin: "1em",
    padding: "1em",
    display: "flex",
    flexDirection: "column",
    gap: "1em",
    backgroundColor: "#f8f8f8",
    border: "1px solid black",
    borderRadius: ".25em",
};

function App() {
    const [module, loading] = useWebAssembly();
    if (loading) console.log("WebAssembly is loading...");
    else {
        module.Log("Web Assembly has loaded!");
    }

    return (
        <div className="App">
            <div style={style}>
                {!loading ? module.Greeting("Aardhyn", "Lavender") : "Loading..."}
            <canvas id="canvas" style={{ border: "1px solid #000", width: '100%', aspectRatio: "16/9", display: "block", margin: "0 auto" }} />
            </div>
        </div>
    );
}

export default App;
