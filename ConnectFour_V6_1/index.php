<?php
session_start();
$_SESSION["loggedIn"] = false;
?>

<?php
include("./includes/header.php");
?>

<div id="login">
    <form method="post" action="./loginhandler.php">
        <label for="user">Username:</label>
        <input type="text" name="user">
        <br>
        <label for="pass">Password:</label>
        <input type="password" name="pass">
        <br> <br>
        <input type="submit" value="Login">
        <br> <br>
        <a href="registerform.php">Register</a>
    </form>
</div>

<div id="response">
    <?php
    if ($_SESSION['err'] ?? false){
        echo $_SESSION["err"];
    }
    $_SESSION["err"] = "";
    ?>
</div>

<?php
include("./includes/footer.html");
?>