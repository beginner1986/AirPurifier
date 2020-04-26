$(function () {
    var manualslider;
    var pmstart;
    var pmend;
    var semiautoslider;
    var pmtype;
    var pmtokeep;
    var pmtypetokeep;
    $('#alert').hide();
        if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
            xmlHttp.open('PUT', 'settings', true);
            xmlHttp.onreadystatechange = handleServerResponse;
            xmlHttp.send(null);

    }

    function handleServerResponse() {
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
            xmlResponse = xmlHttp.responseXML;

            xmldoc = xmlResponse.getElementsByTagName('response');
            manualslider = xmldoc[0].getElementsByTagName('manualslider')[0].childNodes[0].nodeValue;
            pmstart = xmldoc[0].getElementsByTagName('pmstart')[0].childNodes[0].nodeValue;
            pmend = xmldoc[0].getElementsByTagName('pmend')[0].childNodes[0].nodeValue;
            semiautoslider = xmldoc[0].getElementsByTagName('semiautoslider')[0].childNodes[0].nodeValue;
            pmtype = xmldoc[0].getElementsByTagName('pmtype')[0].childNodes[0].nodeValue;
            pmtokeep = xmldoc[0].getElementsByTagName('pmtokeep')[0].childNodes[0].nodeValue;
            pmtypetokeep = xmldoc[0].getElementsByTagName('pmtypetokeep')[0].childNodes[0].nodeValue;
            globalMode = xmldoc[0].getElementsByTagName('mode')[0].childNodes[0].nodeValue; 
            document.getElementById('manualval').innerHTML = manualslider;
            document.getElementById('rangeval').innerHTML = pmstart + " - " + pmend; 
            document.getElementById('semiautoval').innerHTML = semiautoslider;
            document.getElementById('select1').value = pmtype;
            document.getElementById('pmval').innerHTML = pmtokeep;
            document.getElementById('select2').value = pmtypetokeep;
           
        }
    }





    var semiautoslide;
    var rangeslider = [];
    var pmtokeep;
    setTimeout(function () {
    $('#manualslide').slider({
        max: 100,
        min: 0,
        value: manualslider,
        slide: function (e, ui) {
            $('#manualval').html(ui.value); 
        },
        stop: function (e, ui) {
            $.get('/save?manualslider=' + ui.value, function (data) {
            });
        }
    });

    $('#rangeslider').slider({
        range: true,
        min: 0,
        max: 200,
        values: [pmstart, pmend],
        slide: function (event, ui) {
            $('#rangeval').html(ui.values[0] + " - " + ui.values[1]);
            rangeslider[0] = ui.values[0];
            rangeslider[1] = ui.values[1];
        }
    });


    $('#semiautoslide').slider({
        max: 100,
        min: 0,
        value: semiautoslider,
        slide: function (e, ui) {
            $('#semiautoval').html(ui.value);
            semiautoslide = ui.value;
        }
    });
         


    $('#save_semi_button').click(function () {
        var pm = $('#select1').val();
        if (pm >= 1) {
            $.get('/save?pmstart=' + rangeslider[0] + '&pmend=' + rangeslider[1] + '&semiautoslider=' + semiautoslide + '&pmtype=' + pm, function (data) {
            });
            $('#alert').show();
            setTimeout(function () {
                $('#alert').hide();
            }, 2000)
        }
        else
            alert("Wybierz rozmiar PM");
    });




    $('#pmslide').slider({
        max: 200,
        min: 0,
        value: pmtokeep,
        slide: function (e, ui) {
            $('#pmval').html(ui.value);
            pmtokeep = ui.value;
        }
    });
    

    $('#save_auto_button').click(function () {
        var pm = $('#select2').val();
        if (pm >= 1) {
            $.get('/save?pmtokeep=' + pmtokeep + '&pmtypetokeep=' + pm, function (data) {
            });
            $('#alert').show();
            setTimeout(function () {
                $('#alert').hide();
            }, 2000)
        }
        else
            alert("Wybierz rozmiar PM");
    });
    }, 500);
});
