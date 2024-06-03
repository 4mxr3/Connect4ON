<!DOCTYPE html>
<html lang="en">
    <head><meta charset="utf-8">
        <title>Connect 4</title>
        <link rel="stylesheet" href="./includes/main.css">
    </head>
    <body>

        <header>
            <p style="float: left; margin: 0px">Online Connect 4</p>
                <?php
                if ($_SESSION["loggedIn"] == true) {
                    echo '<a href="./index.php" style="max-width: 200px">Logout</a>';
                }
                ?>
            <div id="menu">
                <?php
                if ($_SESSION["loggedIn"] == true) {
                    if ($currUser->getAdmin()) {
                        echo "<a href=''>View all users</a>";
                    }
                    echo "<a href='./displaystats.php'>View your stats</a>";
                    echo "<a href='./playgame.php'>Play a Game</a>";                   
                }
                ?>
            </div>
        </header>
