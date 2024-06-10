<?php
session_start();
$_SESSION["loggedIn"] = false;
?>

<?php
include("./includes/header.php");
?>

<div id="login">
    <form method="post" action="./loginhandler.php" onsubmit="return validateLoginForm()">
        <label for="user">Username:</label>
        <input type="text" name="user" id="user">
        <br>
        <label for="pass">Password:</label>
        <input type="password" name="pass" id="pass">
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

<script>
function validateLoginForm() {
    var user = document.getElementById("user").value;
    var pass = document.getElementById("pass").value;
    if (user === "" || pass === "") {
        alert("Username and Password must be filled out");
        return false;
    }
    return true;
}
</script>

<?php
include("./includes/footer.html");
?>
