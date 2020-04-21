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
        document.getElementById('pm1').innerHTML = xmldoc[0].getElementsByTagName('pm1')[0].childNodes[0].nodeValue + "μg/m3";
        document.getElementById('pm2_5').innerHTML = xmldoc[0].getElementsByTagName('pm2_5')[0].childNodes[0].nodeValue + "μg/m3";
        document.getElementById('pm10').innerHTML = xmldoc[0].getElementsByTagName('pm10')[0].childNodes[0].nodeValue + "μg/m3";
    }
}