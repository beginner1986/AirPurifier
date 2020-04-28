/*!
    * Start Bootstrap - Freelancer v6.0.1 (https://startbootstrap.com/themes/freelancer)
    * Copyright 2013-2020 Start Bootstrap
    * Licensed under MIT (https://github.com/BlackrockDigital/startbootstrap-freelancer/blob/master/LICENSE)
    */
    (function($) {
    "use strict"; // Start of use strict
  
    // Smooth scrolling using jQuery easing
    $('a.js-scroll-trigger[href*="#"]:not([href="#"])').click(function() {
      if (location.pathname.replace(/^\//, '') == this.pathname.replace(/^\//, '') && location.hostname == this.hostname) {
        var target = $(this.hash);
        target = target.length ? target : $('[name=' + this.hash.slice(1) + ']');
        if (target.length) {
          $('html, body').animate({
            scrollTop: (target.offset().top - 71)
          }, 1000, "easeInOutExpo");
          return false;
        }
      }
    });
  
    // Scroll to top button appear
    $(document).scroll(function() {
      var scrollDistance = $(this).scrollTop();
      if (scrollDistance > 100) {
        $('.scroll-to-top').fadeIn();
      } else {
        $('.scroll-to-top').fadeOut();
      }
    });
  
    // Closes responsive menu when a scroll trigger link is clicked
    $('.js-scroll-trigger').click(function() {
      $('.navbar-collapse').collapse('hide');
    });
  
    // Activate scrollspy to add active class to navbar items on scroll
    $('body').scrollspy({
      target: '#mainNav',
      offset: 80
    });
  
    // Collapse Navbar
    var navbarCollapse = function() {
      if ($("#mainNav").offset().top > 100) {
        $("#mainNav").addClass("navbar-shrink");
      } else {
        $("#mainNav").removeClass("navbar-shrink");
      }
    };
    // Collapse now if page is not at top
    navbarCollapse();
    // Collapse the navbar when page is scrolled
    $(window).scroll(navbarCollapse);
  
  })(jQuery); // End of use strict

function showInfo() {
    document.getElementById('settings').style.display = 'none';
    document.getElementById('contact').style.display = 'none';
    document.getElementById('info').style.display = 'block';
}
 
function showSettings() {
    document.getElementById('contact').style.display = 'none';
    document.getElementById('info').style.display = 'none';
    document.getElementById('settings').style.display = 'block';
}

function showContact() {
    document.getElementById('settings').style.display = 'none';
    document.getElementById('info').style.display = 'none';
    document.getElementById('contact').style.display = 'block';
}





$(document).ready(function () {
    $("div.desc").hide();
    $("input[name$='options']").click(function () {
        var test = $(this).val();
        $("div.desc").hide();
        $("#" + test).show();
        switch (test) {
            case "manual": {
                globalMode = 1;
                $.get('/save?mode=' + globalMode, function (data) { });
                break;
            }
            case "semiauto": {
                globalMode = 2;
                $.get('/save?mode=' + globalMode, function (data) { });
                break;
            }
            case "auto": {
                globalMode = 3;
                $.get('/save?mode=' + globalMode, function (data) { });
                break;
            }
            case "off": {
                globalMode = 4;
                $.get('/save?mode=' + globalMode, function (data) { });
                break;
            }
        }

    });
});

$(document).ready(function () {
    setTimeout(function () {
        switch (globalMode) {
            case "1": {
                $("#option1").trigger('click');
                $("#manual").show();
                break;
            }
            case "2": {
                $("#option2").trigger('click');
                $("#semiauto").show();
                break;
            }
            case "3": {
                $("#option3").trigger('click');
                $("#auto").show();
                break;
            }
            case "4": {
                $("#option4").trigger('click');
                $("#off").show();
                break;

            }
        }
    }, 1000);
});

// append css and js files from file system if internet connection or files are unavailable
function loadCssOffline(file) {
    var link = document.createElement('link');
    link.rel = 'stylesheet';
    link.type = 'text/css';
    link.href = file;
    document.getElementsByTagName('head')[0].appendChild(link);
}

function loadJsOffline(file) {
    var script = document.createElement('script');
    script.href = file;

    document.getElementsByTagName('body')[0].appendChild(script);
}