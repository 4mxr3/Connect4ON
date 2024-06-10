<?php
session_start();
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <title>Connect 4</title>
    <link rel="stylesheet" href="./includes/main.css">
</head>
<body>

<header>
    <div class="header-left">
        <p>Online Connect 4</p>
    </div>
    <div class="header-center">
        <?php
        if (isset($_SESSION["loggedIn"]) && $_SESSION["loggedIn"] == true) {
            echo "<a href='./playgame.php'>Play a Game</a>";
            echo "<a href='./displaystats.php'>View your stats</a>";
            if (isset($currUser) && $currUser->getAdmin()) {
                echo "<a href='./allusers.php'>View all users</a>";
            }
        }
        ?>
    </div>
    <div class="header-right">
        <?php
        if (isset($_SESSION["loggedIn"]) && $_SESSION["loggedIn"] == true) {
            echo '<a href="./index.php">Logout</a>';
        }
        ?>
    </div>
</header>
