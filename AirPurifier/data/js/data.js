var xmlHttp = createXmlHttpObject();

function createXmlHttpObject() {
    if (window.XMLHttpRequest) {
        xmlHttp = new XMLHttpRequest();
    } else {
        xmlHttp = new ActiveXObject('Microsoft.XMLHTTP');
    }
    return xmlHttp;
}

function process() {
    if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
        xmlHttp.open('PUT', 'xml', true);
        xmlHttp.onreadystatechange = handleServerResponse;
        xmlHttp.send(null);
    }
    setTimeout('process()', 2000);
}

function handleServerResponse() {
    if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
        xmlResponse = xmlHttp.responseXML;

        xmldoc = xmlResponse.getElementsByTagName('response');
        var pm1 = xmldoc[0].getElementsByTagName('pm1')[0].childNodes[0].nodeValue;
        var pm2_5 = xmldoc[0].getElementsByTagName('pm2_5')[0].childNodes[0].nodeValue;
        var pm10 = xmldoc[0].getElementsByTagName('pm10')[0].childNodes[0].nodeValue;
        var temperature = xmldoc[0].getElementsByTagName('temperature')[0].childNodes[0].nodeValue;
        var pressure = xmldoc[0].getElementsByTagName('pressure')[0].childNodes[0].nodeValue;
        var humidity = xmldoc[0].getElementsByTagName('humidity')[0].childNodes[0].nodeValue;
        globalMode = xmldoc[0].getElementsByTagName('mode')[0].childNodes[0].nodeValue;
        document.getElementById('pm1').innerHTML = pm1 + " &microg/m<sup>3</sup>";
        document.getElementById('pm2_5').innerHTML = pm2_5 + " &microg/m<sup>3</sup>";
        document.getElementById('pm10').innerHTML = pm10 + " &microg/m<sup>3</sup>";
        document.getElementById('temperature').innerHTML = temperature + " &deg;C";
        document.getElementById('pressure').innerHTML = pressure + " hPa";
        document.getElementById('humidity').innerHTML = humidity + " %";

        if (pm1 > 50) {
            document.getElementById('pm1').style.color = 'red';
        } else if (pm1 > 20) {
            document.getElementById('pm1').style.color = '#ff6a00';
        } else {
            document.getElementById('pm1').style.color = 'black';
        }

        if (pm2_5 > 50) {
            document.getElementById('pm2_5').style.color = 'red';
        } else if (pm2_5 > 20) {
            document.getElementById('pm2_5').style.color = '#ff6a00';
        } else {
            document.getElementById('pm2_5').style.color = 'black';
        }

        if (pm10 > 50) {
            document.getElementById('pm10').style.color = 'red';
        } else if (pm10 > 20) {
            document.getElementById('pm10').style.color = '#ff6a00';
        } else {
            document.getElementById('pm10').style.color = 'black';
        }

        if (humidity >= 70) {
            document.getElementById('humidity').style.color = 'red';
        } else {
            document.getElementById('humidity').style.color = 'black';
        }

        if (temperature <= -10 || temperature >= 50) {
            document.getElementById('temperature').style.color = 'red';
        } else {
            document.getElementById('temperature').style.color = 'black';
        }

        if (pressure <= 860 || pressure >= 1100) {
            document.getElementById('pressure').style.color = 'red';
        } else {
            document.getElementById('pressure').style.color = 'black';
        }

        showPmTiles(pm1);
    }
}
