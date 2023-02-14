const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="zh-Hant">
<head>
    
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0"><!--網頁概述-->
    <title>wifi website</title>    
    <style>
    </style>
</head>
<body class="light-theme">
    <h1 class="welcome">WiFi STA</h1>    
    <br>
    <button class = "switcher">change mode</button>
    <form action='/test' method='post'><!--按下submit，瀏覽器訪問/test，且用post方法-->
    <label for="ssid">SSID: </label>
    <input type='text' name='ssid' value=''><br>
    <label for="pwd">PWD: </label>
    <input type='text' name='pwd' value=''><br>
    <input type='submit' value='connect'>
    </form>
    <div>
        <label for="switch">AP: </label>
        <button class = "switch">ON</button>
    </div>
    <script>
      "use strict";//嚴格模式 eg.不能使用未定義的參數(ES6)

      const button = document.querySelector('.switch');

      button.addEventListener('click', function () {
          if (button.textContent === 'ON') {
              button.textContent = 'OFF';
          } else {
              button.textContent = 'ON';
          }
      });
    </script>
</body>
</html>
)=====";