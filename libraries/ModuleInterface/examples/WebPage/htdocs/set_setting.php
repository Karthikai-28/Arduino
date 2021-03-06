<?php
// Insert or update the supplied JSON name:value pair in the settings table.
if(isset($_POST))
{
	// Database settings
	include "db_config.php";

	foreach($_POST as $field_name => $val)
	{
		// Clean post values
		$conn = new PDO("mysql:host=$server;dbname=$database;charset=utf8", $username, $password);
		$field_id = strip_tags(trim($field_name));
		if (isset($val)) $val = strip_tags(trim($val));

		if(!empty($field_id) && isset($val) && $val != "")
		{
			// Update the values
			$sql = "INSERT INTO settings (id, value) VALUES(:field_id, :valA) ON DUPLICATE KEY UPDATE value=:valB";
			try {			
				$conn ->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
				
				// Prepare statement
				$stmt = $conn->prepare($sql);
	
				// Execute the query
				$stmt->execute( array(':field_id' => $field_id, ':valA' => $val, ':valB' => $val));

				// Echo a message to say the UPDATE succeeded
				echo $stmt->rowCount() . " records UPDATED successfully";
			}
			catch(PDOException $e)
			{
				echo $sql . "<br>" . $e->getMessage();
			}
		} else {
			echo "Invalid Requests";
		}
	}
} else {
	echo "Invalid Requests";
}
?>