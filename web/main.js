var background_color = document.getElementsByTagName("body")
var foreground_color = document.getElementById("main")
var button = document.getElementsByTagName("button")

/*window.onload = function() 
{
    
};*/

function ready()
{    
    background_color[0].style.backgroundColor = "black";
    foreground_color.style.color = "white";
    button[0].style.visibility = "visible";
}

function theme()
{
    if (background_color[0].style.backgroundColor == "white")
    {
        background_color[0].style.backgroundColor = "black"
        foreground_color.style.color = "white"
        return
    }

    else
    {
        background_color[0].style.backgroundColor = "white"
        foreground_color.style.color = "black"
        return
    }
}