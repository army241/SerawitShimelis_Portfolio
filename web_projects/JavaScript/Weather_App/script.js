const button = document.getElementById("get-weather-btn");
const select = document.getElementById("city-select");

async function getWeather(city) {

  try {

    const response = await fetch(
      `https://weather-proxy.freecodecamp.rocks/api/city/${city}`
    );

    const data = await response.json();

    return data;

  } catch (error) {

    console.error(error);
    return undefined;

  }

}

async function showWeather(city) {

  const data = await getWeather(city);

  if (!data) {
    alert("Something went wrong, please try again later");
    return;
  }

  const weather = data.weather?.[0];

  document.getElementById("location").textContent =
    data.name || "N/A";

  document.getElementById("weather-main").textContent =
    weather?.main || "N/A";

  document.getElementById("main-temperature").textContent =
    data.main?.temp ?? "N/A";

  document.getElementById("feels-like").textContent =
    data.main?.feels_like ?? "N/A";

  document.getElementById("humidity").textContent =
    data.main?.humidity ?? "N/A";

  document.getElementById("wind").textContent =
    data.wind?.speed ?? "N/A";

  document.getElementById("wind-gust").textContent =
    data.wind?.gust ?? "N/A";

  const icon = weather?.icon;

  const iconElement = document.getElementById("weather-icon");

  if (icon) {
    iconElement.src = icon;
  } else {
    iconElement.src = "";
  }

}

button.addEventListener("click", () => {

  const city = select.value;

  if (!city) return;

  showWeather(city);

});