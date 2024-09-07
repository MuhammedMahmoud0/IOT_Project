import 'package:firebase_core/firebase_core.dart'; // Import firebase_core dependency
import 'package:flutter/material.dart';
import 'login_page.dart';

Future<void> main() async {
  WidgetsFlutterBinding
      .ensureInitialized(); // It's a need for the application to have these to work
  await Firebase.initializeApp(
    //add your project details by going to your project settings
    options: const FirebaseOptions(
        apiKey: "AIzaSyAlZuxjipX2acMPVvixEmvgL6LWCM3I42c",
        authDomain: "test-94545.firebaseapp.com",
        projectId: "test-94545",
        storageBucket: "test-94545.appspot.com",
        messagingSenderId: "286781232548",
        appId: "1:286781232548:android:4d96b879a5e4010dc45d31"),
  );
  runApp(MyApp());
}

// Set the login page as the home page which the application starts with.
class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: LoginPage(),
      debugShowCheckedModeBanner: false,
    );
  }
}
