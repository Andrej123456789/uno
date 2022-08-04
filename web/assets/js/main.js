var body = document.querySelector('body');
var button = document.querySelector('button');
var main = document.getElementById('main');

function theme()
{
    let current_theme = window.getComputedStyle(main, null).getPropertyValue("background-color");
    let new_theme = null;

    if (current_theme == 'rgb(52, 58, 64)')
    {
        current_theme = "gray";
    }

    new_theme = randomTheme();

    if (new_theme == "dark")
    {
        body.style.backgroundColor = "black";
        button.style.backgroundColor = "black";
    }

    else if (new_theme == "light")
    {
        body.style.backgroundColor = "white";
        button.style.backgroundColor = "white";
    }

    else
    {
        body.style.backgroundColor = new_theme;
        button.style.backgroundColor = new_theme;
    }

    switch (new_theme) 
    {
        case 'gray':
            main.style.color = 'white';
            button.style.color = 'white';
            button.style.borderColor = 'white';
            break;

        case 'dark':
            main.style.color = 'white';
            button.style.color = 'white';
            button.style.borderColor = 'gray';
            break;

        case 'light':
            main.style.color = 'black';
            button.style.color = 'black';
            button.style.borderColor = 'gray';
            break;

        case 'pink':
            main.style.color = 'black';
            button.style.color = 'black';
            button.style.borderColor = 'gray';
            break;

        case 'yellow':
            main.style.color = 'black';
            button.style.color = 'black';
            button.style.borderColor = 'gray';
            break;

        case 'aqua':
            main.style.color = 'black';
            button.style.color = 'black';
            button.style.borderColor = 'gray';
            break;

        case 'purple':
            main.style.color = 'white';
            button.style.color = 'white';
            button.style.borderColor = 'gray';
            break;

        case 'darkred':
            main.style.color = 'white';
            button.style.color = 'white';
            button.style.borderColor = 'gray';
            break;
    
        default:
            break;
    }
}

function randomTheme()
{
    const themes = ['gray', 'dark', 'light', 'pink', 'yellow', 'aqua', 'purple', 'darkred'];
    return themes[Math.floor(Math.random() * themes.length)];
}
