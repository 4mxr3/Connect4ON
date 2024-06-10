function sortTable(col, order) {
    var index, table, rows, switching, i, x, y, shouldSwitch;

    if (col == "time") {
        index = 2;
    } else
        index = col;
    table = document.getElementById("reportTable");
    switching = true;

    while (switching) {
        switching = false;
        //Get rows with data and loop through all of them
        rows = table.rows;
        for (i = 1; i < (rows.length - 1); i++) {
            shouldSwitch = false;
            //Get two adjacent rows, then compare
            x = rows[i].getElementsByTagName("TD")[index];
            y = rows[i + 1].getElementsByTagName("TD")[index];

            if (order == 0) {
                if (x.innerHTML.toLowerCase() > y.innerHTML.toLowerCase()) {
                    // If swap needed, mark as a switch and break the loop to switch and restart
                    shouldSwitch = true;
                    break;
                }
            } else if (x.innerHTML.toLowerCase() < y.innerHTML.toLowerCase()) {
                // If swap needed, mark as a switch and break the loop to switch and restart
                shouldSwitch = true;
                break;
            }

        }
        if (shouldSwitch) {
            //Make switch and mark sentinel value as true to restart the sorting loop
            rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
            switching = true;
        }
    }
}

function filter(){
    var input,filter,tab,tr,td,rowTxt;
    
    //Get input in filter box
    input = document.getElementById("input");
    filter = input.value.toUpperCase();
    //Get table elements
    tab = document.getElementById("reportTable");
    tr = tab.getElementsByTagName("tr");

    for (var i = 0; i < tr.length; i++){
        
        //Get each row's text
        td = tr[i].getElementsByTagName("td")[0];
        if (td){
            
            rowTxt = td.textContent || td.innerText;
            //Then see if filter values exist in text value
            if (rowTxt.toUpperCase().indexOf(filter) > -1){
                tr[i].style.display = "";
                
            }else tr[i].style.display = "none"; //If not, don't display
        }
    }
}

function showEditForm(user){
    section = document.getElementById('login');

    section.innerHTML = '<input type="hidden" name="u" value="' + user.username +'">';
    section.innerHTML += '<input type="hidden" name="p" value="' + user.password +'">';
    
    section.innerHTML += '<label for="username">Username:</label>';
    section.innerHTML += '<input type="text" name="username" value="' + user.username +'" required>';
    section.innerHTML += '<br>';
    section.innerHTML += '<label for="password">Password:</label>';
    section.innerHTML += '<input type="text" name="password" value="' + user.password +'" required>';
    section.innerHTML += '<br>';
    section.innerHTML += '<label for="fname">First Name:</label>';
    section.innerHTML += '<input type="text" name="fname" value="' + user.fname +'" required>';
    section.innerHTML += '<br>';
    section.innerHTML += '<label for="lname">Last Name:</label>';
    section.innerHTML += '<input type="text" name="lname" value="' + user.lname +'" required>';
    section.innerHTML += '<br>';
    section.innerHTML += '<label for="wins">Wins:</label>';
    section.innerHTML += '<input type="number" name="wins" value="' + user.wins +'" required>';
    section.innerHTML += '<br>';
    section.innerHTML += '<label for="losses">Losses:</label>';
    section.innerHTML += '<input type="number" name="losses" value="' + user.losses +'" required>';
    section.innerHTML += '<br>';
    section.innerHTML += '<label for="ties">Ties:</label>';
    section.innerHTML += '<input type="number" name="ties" value="' + user.ties +'" required>';
    section.innerHTML += '<br>';
    section.innerHTML += '<label for="admin">Admin:</label>';
    if(user.admin == 1){
        section.innerHTML += 'Yes<input type="radio" name="admin" value="1" checked>';
        section.innerHTML += 'No<input type="radio" name="admin" value="0">';
    }else {
        section.innerHTML += 'Yes<input type="radio" name="admin" value="1" >';
        section.innerHTML += 'No<input type="radio" name="admin" value="0" checked>';
    }
    section.innerHTML += '<br><input type="submit" value="Save">';
    section.innerHTML += '<button type="reset">Reset to current values</button> <br><br>';
}