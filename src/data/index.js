let led_id1 = document.getElementById("led1");
let led_id1_status = document.getElementById("led1_status");
let led_id2 = document.getElementById("led2");
let led_id2_status = document.getElementById("led2_status");

const led1 = async () => {
  fetch("/led1-device", {
    method: "POST", // or 'PUT'
    body: JSON.stringify({
      GPIO1: led_id1.textContent === "ON" ? false : true,
    }), // data can be `string` or {object}!
    headers: {
      "Content-Type": "application/json",
    },
  })
    .then((res) => res.json())
    .catch((error) => console.error("Error:", error))
    .then((response) => {
      {
        console.log("Success:", response);
        if (response.GPIO1 === true) {
          led_id1.textContent = "ON";
          led_id1_status.textContent = "ON";
          led_id1.classList.remove("button-off");
          led_id1.classList.add("button-on");
        } else {
          led_id1.textContent = "OFF";
          led_id1_status.textContent = "OFF";
          led_id1.classList.remove("button-on");
          led_id1.classList.add("button-off");
        }
      }
    });
};

const led2 = async () => {
  await fetch("/led2-device", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({
      GPIO2: led_id2.textContent === "ON" ? false : true,
    }),
  })
    .then((res) => res.json())
    .catch((error) => console.error("Error:", error))
    .then((response) => {
      {
        console.log("Success:", response);
        if (response.GPIO2 === true) {
          led_id2.textContent = "ON";
          led_id2_status.textContent = "ON";
          led_id2.classList.remove("button-off");
          led_id2.classList.add("button-on");
        } else {
          led_id2.textContent = "OFF";
          led_id2_status.textContent = "OFF";
          led_id2.classList.remove("button-on");
          led_id2.classList.add("button-off");
        }
      }
    });
};
