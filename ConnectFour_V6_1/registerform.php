<?php
session_start();
$_SESSION["loggedIn"] = false;
?>

<?php
include("./includes/header.php");
?>

<div id="login">
    <form method="post" action="./registerhandler.php">
        <label for="user">Username:</label>
        <input type="text" name="user">
        <br>
        <label for="pass">Password:</label>
        <input type="text" name="pass">
        <br>
        <label for="fname">First Name:</label>
        <input type="text" name="fname">
        <br>
        <label for="lname">Last Name:</label>
        <input type="text" name="lname">
        <br>
        <label for="admin">Admin:</label>
        Yes<input type="radio" name="admin" value="1">
        No<input type="radio" name="admin" value="0" checked>
        <br> <br>
        <input type="submit" value="Register">
        <br> <br>
    </form>
</div>

<div id="response">
    <?php
    echo $_SESSION["err"];
    $_SESSION["err"] = "";
    ?>
</div>

<?php
include("./includes/footer.html");
?>
