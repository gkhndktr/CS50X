function validateForm() {
  var x = document.forms["contact"]["name"].value;
  if (x == "") {
    alert("Name must be filled out");
    return false;
      }
  var y = document.forms["contact"]["mail"].value;
  if (y == "") {
    alert("email must be filled out");
    return false;
      }
      }