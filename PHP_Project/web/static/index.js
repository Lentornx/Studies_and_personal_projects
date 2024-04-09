    function load() 
    {
        let x = sessionStorage.getItem("Name");
            document.forms["myForm"]["name"].value = x;
        x = sessionStorage.getItem("Age");
            document.forms["myForm"]["age"].value = x;
        x = sessionStorage.getItem("Radio");
            document.forms["myForm"]["radio"].value = x;
        x = sessionStorage.getItem("Check1");
            if(x==1) {document.getElementById("c1").checked=true}
            else {document.getElementById("c1").checked=false};
        x = sessionStorage.getItem("Check2");
            if(x==1) {document.getElementById("c2").checked=true}
            else {document.getElementById("c2").checked=false};
        x = sessionStorage.getItem("Check3");
            if(x==1) {document.getElementById("c3").checked=true}
            else {document.getElementById("c3").checked=false};
        x = sessionStorage.getItem("Check4");
            if(x==1) {document.getElementById("c4").checked=true}
            else {document.getElementById("c4").checked=false};
        x = sessionStorage.getItem("Selection");
            document.forms["myForm"]["select"].value = x;
        x = sessionStorage.getItem("Explanation");
            document.forms["myForm"]["explanation"].value = x;
        x = sessionStorage.getItem("Suggestions");
            document.forms["myForm"]["suggestions"].value = x;    }
    function save()
    {
        let x = document.forms["myForm"]["name"].value;
            sessionStorage.setItem("Name",x);
        x = document.forms["myForm"]["age"].value;
            sessionStorage.setItem("Age",x);
        x = document.forms["myForm"]["radio"].value;
            sessionStorage.setItem("Radio",x);
        if(document.getElementById("c1").checked==true) {x=1} else{x=0};
            sessionStorage.setItem("Check1",x);
        if(document.getElementById("c2").checked==true) {x=1} else{x=0};
            sessionStorage.setItem("Check2",x);
        if(document.getElementById("c3").checked==true) {x=1} else{x=0};
            sessionStorage.setItem("Check3",x);
        if(document.getElementById("c4").checked==true) {x=1} else{x=0};
            sessionStorage.setItem("Check4",x);
        x = document.forms["myForm"]["select"].value;
            sessionStorage.setItem("Selection",x);
        x = document.forms["myForm"]["explanation"].value;
            sessionStorage.setItem("Explanation",x);
        x = document.forms["myForm"]["suggestions"].value;
            sessionStorage.setItem("Suggestions",x);
    }
    function darkMode()
    {
        let x = document.getElementById("darkModeButton").innerHTML;
        if (x == "toggle brightmode")
        { 
            let classSelector = document.querySelectorAll('.ciekawostka');
            classSelector.forEach(ciekawostka => {
                ciekawostka.style.backgroundColor = "rgb(0, 81, 255)";
                ciekawostka.style.color = "rgb(0, 81, 255)";})
            localStorage.setItem("dark_bright","itIsBright");
            document.getElementById("darkModeButton").innerHTML = "toggle darkmode";
            document.getElementById("html").style.backgroundColor = "sandybrown";
            document.getElementById("html").style.Color = "rgb(138, 32, 32)";
            document.getElementById("content").style.backgroundColor = "antiquewhite";
            document.getElementById("nav").style.backgroundColor = "antiquewhite";
            document.getElementById("header").style.backgroundColor = "rgb(138, 32, 32)";
            document.getElementById("footer").style.backgroundColor = "rgb(138, 32, 32)";
            if(document.getElementById("dialog")!=null) {document.getElementById("dialog").style.backgroundColor = "antiquewhite"}; 
        }
        else
        {
            let classSelector = document.querySelectorAll('.ciekawostka');
            classSelector.forEach(ciekawostka => {
                ciekawostka.style.backgroundColor = "rgb(37, 82, 177)"; 
                ciekawostka.style.color = "rgb(37, 82, 177)";})
            localStorage.setItem("dark_bright","itIsDark");
            document.getElementById("darkModeButton").innerHTML = "toggle brightmode";
            document.getElementById("html").style.backgroundColor = "rgb(148, 112, 81)";
            document.getElementById("html").style.Color = "rgb(108, 34, 34)";
            document.getElementById("content").style.backgroundColor = "rgb(198, 193, 187)";
            document.getElementById("nav").style.backgroundColor = "rgb(198, 193, 187)";
            document.getElementById("header").style.backgroundColor = "rgb(108, 34, 34)";
            document.getElementById("footer").style.backgroundColor = "rgb(108, 34, 34)";
           if(document.getElementById("dialog")!=null) {document.getElementById("dialog").style.backgroundColor = "rgb(198, 193, 187)"};
        }
    }
    function onLoad()
    {
        {
            let darkModeButton = document.createElement("button");
            darkModeButton.setAttribute("id","darkModeButton");
            darkModeButton.setAttribute("onclick","darkMode()");
            let darkModeButtonText = document.createTextNode("toggle darkmode");
            darkModeButton.appendChild(darkModeButtonText);
            let darkModeButtonDiv = document.getElementById("darkMode");
            darkModeButtonDiv.appendChild(darkModeButton);
        }   
        {
            let classSelector = document.querySelectorAll('.ciekawostka');
            classSelector.forEach(ciekawostka => {
                ciekawostka.style.backgroundColor = "rgb(0, 81, 255)";
                ciekawostka.style.color = "rgb(0, 81, 255)";})
        }
        {
            if (localStorage.getItem("dark_bright")!=null) {let x = localStorage.getItem("dark_bright");
            if (x=="itIsDark"){darkMode();}}
        }
    }

    $(document).ready(function(){
        $(".ciekawostka").mouseenter(function(){
            $(this).animate({color: "antiquewhite"});
        });
        $("#saveButton").click(function(){
            $( "#dialog" ).dialog({
                position: {
                    at: "right center"
                },
                width: 100,
                height: 100,
            });
        }) 
        $(function(){
            $( "#datePick" ).datepicker();
        });
    });

