<!-- registerform.php -->

<?php
session_start();
$_SESSION["loggedIn"] = false;
?>

<?php
include("./includes/header.php");
?>

<div id="login">
    <form method="post" action="./registerhandler.php" onsubmit="return validateRegisterForm()">
        <div>
            <label for="user">Username:</label>
            <input type="text" name="user" id="user">
        </div>
        <div>
            <label for="pass">Password:</label>
            <input type="text" name="pass" id="pass">
        </div>
        <div>
            <label for="fname">First Name:</label>
            <input type="text" name="fname" id="fname">
        </div>
        <div>
            <label for="lname">Last Name:</label>
            <input type="text" name="lname" id="lname">
        </div>
        <div class="radio-group">
            <label for="admin">Admin:</label>
            Yes<input type="radio" name="admin" value="1">
            No<input type="radio" name="admin" value="0" checked>
        </div>
        <div class="submit-group">
            <input type="submit" value="Register" class="spacing">
            <button type="button" class="spacing" onclick="window.location.href='./index.php'">Return to Login Menu</button>
        </div>
    </form>
</div>

<style>
    .submit-group {
        display: flex;
        flex-direction: column;
        align-items: center; /* Centers the buttons horizontally */
    }
    .submit-group .spacing {
        margin-bottom: 10px; /* Adjust the spacing as needed */
    }
</style>

<div id="response">
    <?php
    echo $_SESSION["err"];
    $_SESSION["err"] = "";
    ?>
</div>

<script>
function validateRegisterForm() {
    var user = document.getElementById("user").value;
    var pass = document.getElementById("pass").value;
    var fname = document.getElementById("fname").value;
    var lname = document.getElementById("lname").value;

    if (user === "" || pass === "" || fname === "" || lname === "") {
        alert("All fields must be filled out");
        return false;
    }

    if (pass.length < 5) {
        alert("Password must be at least 5 characters long");
        return false;
    }

    return true;
}
</script>

<?php
include("./includes/footer.html");
?>
