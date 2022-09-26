let led_id1 = document.getElementById("led1");
let led_id1_status = document.getElementById("led1_status");
let led_id2 = document.getElementById("led2");
let led_id2_status = document.getElementById("led2_status");

const style_handle = (condition, ledID, ledStatus) => {
  if (condition === true) {
    ledID.textContent = "ON";
    ledStatus.textContent = "ON";
    ledID.classList.remove("button-off");
    ledID.classList.add("button-on");
  } else {
    ledID.textContent = "OFF";
    ledStatus.textContent = "OFF";
    ledID.classList.remove("button-on");
    ledID.classList.add("button-off");
  }
};

const led = async (Url, GPIO, ledID, ledStatus) => {
  const value = ledID.textContent === "ON" ? false : true;
  const jsonObj = JSON.parse(`{"${GPIO}": ${value}}`);

  const data_led = await fetch(`${Url}`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(jsonObj),
  });

  const response_led = await data_led.json();
  const jsonValueString = JSON.stringify(response_led);
  if (response_led) {
    console.log("Respuesta generica :", response_led);
    style_handle(jsonValueString.includes("true"), ledID, ledStatus);
  }
};

const led1 = async () => {
  await led("/led1-device", "GPIO1", led_id1, led_id1_status);
};

const led2 = async () => {
  await led("/led2-device", "GPIO2", led_id2, led_id2_status);
};
