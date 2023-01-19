package com.hakudan.myloginapp;

import android.os.Bundle;
import android.view.MenuItem;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentTransaction;

import com.google.android.material.bottomnavigation.BottomNavigationView;
import com.google.android.material.navigation.NavigationBarView;

public class DashboardActivity extends AppCompatActivity {

   BottomNavigationView bottomNavigationView;

   HomeFragment homeFragment = new HomeFragment();
   FriendsFragment friendsFragment = new FriendsFragment();
   SharePlacesFragment sharePlacesFragment = new SharePlacesFragment();
   ProfileFragment profileFragment = new ProfileFragment();

   @Override
    protected void onCreate(Bundle savedInstanceState){
       super.onCreate(savedInstanceState);
       setContentView(R.layout.activity_dashboard);

       bottomNavigationView = findViewById(R.id.bottom_navigation);

       getSupportFragmentManager().beginTransaction().replace(R.id.container,homeFragment).commit();

       bottomNavigationView.setOnItemSelectedListener(new NavigationBarView.OnItemSelectedListener() {
           @Override
           public boolean onNavigationItemSelected(@NonNull MenuItem item) {
               switch (item.getItemId()){
                   case R.id.nav_home:
                       getSupportFragmentManager().beginTransaction().replace(R.id.container,homeFragment).commit();
                       return true;
                   case R.id.nav_friends:
                       getSupportFragmentManager().beginTransaction().replace(R.id.container,friendsFragment).commit();
                       return true;
                   case R.id.nav_shareplaces:
                       getSupportFragmentManager().beginTransaction().replace(R.id.container,sharePlacesFragment).commit();
                       return true;
                   case R.id.nav_profile:
                       getSupportFragmentManager().beginTransaction().replace(R.id.container,profileFragment).commit();
                       return true;
               }
               return false;
           }
       });
   }
}
