const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="zh-Hant">

<head>
   <meta charset="UTF-8">
   <meta http-equiv="X-UA-Compatible" content="IE=edge">
   <meta name="viewport" content="width=device-width, initial-scale=1.0">
   <title>wifi website</title>
   <style>
      .mode {
         /*改背景*/
         position: absolute;
         top: 20px;
         left: 500px;
         height: 50px;
         width: 50px;
         border-radius: 50%;
         border: 1px dotted black;
         color: var(--btnFontColor);
         background-color: var(--btnBg);
      }

      .wifiAP {
         display: none;
      }
   </style>

</head>

<body>
   <h1 class="welcome">WiFi</h1>
   <br>
   <button class="mode" id="modeBtn">change mode</button>
   <div class="wifiSTA" style="display: block;">
      <form action='/wifi' method='post' class="wifiForm"><!--按下submit，瀏覽器訪問/wifi，且用post方法-->
         <label for="ssid">SSID: </label>
         <input type='text' name='ssid' value=''><br>
         <label for="pwd">PWD: </label>
         <input type='password' name='pwd' value=''><br>
         <input type='submit' value='connect'>
      </form>
   </div>
   <div class="wifiAP" id="apMdoe">
      <label for="apSwitch">AP: </label>
      <button class="apSwitch" id="apBtn">ON</button>
   </div>

   <script>
      "use strict";
      const apButton = document.querySelector('#apBtn');
      const modeButton = document.querySelector('#modeBtn');
      const wifiAP = document.querySelector('.wifiAP');
      const wifiSTA = document.querySelector('.wifiSTA');

      function modeAlert() {
         var alertMsg;
         alertMsg = wifiSTA.style.display === 'none' ? 'AP mode' : 'WiFi mode';
         alert(alertMsg);
      }
      function apAlert(apStutus) {
         var alertMsg;
         alertMsg = apStutus === 'ON' ? 'AP OFF' : 'AP ON\nAP name: Matrix-310\npassword: 00000000';
         alert(alertMsg);
      }
      modeButton.addEventListener('click', function () {
         if (wifiSTA.style.display === 'block') {
            wifiSTA.style.display = 'none';
            wifiAP.style.display = 'block';
            modeAlert();
         }
         else {
            wifiSTA.style.display = 'block';
            wifiAP.style.display = 'none';
            modeAlert();
         }
      });
      apButton.addEventListener('click', function () {
         var apStutus;
         if (apButton.textContent === 'ON') {
            apButton.textContent = 'OFF';
            apStutus = apButton.textContent;
            apAlert(apStutus);
            postApSatus();
         } else {
            apButton.textContent = 'ON';
            apStutus = apButton.textContent;
            apAlert(apStutus);
            postApSatus();
         }
      });
      document.querySelector('wifiForm').addEventListener('submit', function(event) {
         event.preventDefault(); // 防止表單被正常提交
       
         // 取得SSID和PWD的值
         var ssid = document.querySelector('input[name="ssid"]').value;
         var pwd = document.querySelector('input[name="pwd"]').value;
       
         // 建立XMLHttpRequest物件
         var xhr = new XMLHttpRequest();
       
         // 設定傳送的目標網址
         xhr.open('POST', '/wifi', true);
       
         // 設定要傳送的資料格式
         xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
       
         // 設定傳送的資料，格式為「key1=value1&key2=value2」
         var data = 'ssid=' + encodeURIComponent(ssid) + '&pwd=' + encodeURIComponent(pwd);
       
         // 傳送資料
         xhr.send(data);
       
         // 傳送完成後的動作
         xhr.addEventListener('load', function() {
           console.log('Response:', xhr.responseText);
         });
       });
      function postApSatus() {
         var xhttp = new XMLHttpRequest();
         const formData = new FormData();
         formData.append('buttonText', apButton.textContent);
         xhttp.open("POST", "/ap", true);
         xhttp.send(formData);
      }
   </script>
</body>

</html>
)=====";