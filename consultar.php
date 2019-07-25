
<?php
$username = $_POST['name'];
$pass = $_POST['password'];

		$conn = mysqli_connect('localhost','id10249898_ing_software','contrasena','id10249898_smartapp');
			if (mysqli_connect_errno()){
				echo "Error de conexión: ".mysqli_connect_errno();
			}

		$agregar = mysqli_query($conn,"select * from usuario where name='$username' and password='$pass'");

		if (mysqli_num_rows($agregar)>0){
		    echo 'login_ok';
		}
		else{
		    echo 'error_login';
		}



		mysqli_close($conn);


?>

