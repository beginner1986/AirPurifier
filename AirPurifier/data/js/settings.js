$(function () {
    var semiautoslide;
    var rangeslider = [];
    var pmtokeep;
    $('#manualslide').slider({
        max: 100,
        min: 0,
        value: 0,
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
        values: [20, 60],
        slide: function (event, ui) {
            $('#rangeval').html(ui.values[0] + " - " + ui.values[1]);
            rangeslider[0] = ui.values[0];
            rangeslider[1] = ui.values[1];
        }
    });


    $('#semiautoslide').slider({
        max: 100,
        min: 0,
        value: 0,
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
        }
        else
            alert("Wybierz rozmiar PM");
    });




    $('#pmslide').slider({
        max: 200,
        min: 0,
        value: 0,
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
        }
        else
            alert("Wybierz rozmiar PM");
    });

});
