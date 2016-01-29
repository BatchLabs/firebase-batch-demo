package com.batch.labs.firebase;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends BaseActivity
{

	private EditText loginServiceEditText;
	private EditText uidEditText;

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		loginServiceEditText = (EditText) findViewById(R.id.login_service_edittext);
		uidEditText = (EditText) findViewById(R.id.user_id_edittext);

		findViewById(R.id.logout_button).setOnClickListener(new View.OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				UserProfileManager.getInstance().logout();
				showLogin();
			}
		});

		if (!UserProfileManager.getInstance().isLoggedIn()) {
			showLogin();
		}
	}

	@Override
	protected void onStart()
	{
		super.onStart();

		String loginServiceName;

		switch (UserProfileManager.getInstance().getCurrentLoginType()) {
			case GOOGLE:
				loginServiceName = "Google Sign-In";
				break;
			case ANONYMOUS:
				loginServiceName = "Anonymous";
				break;
			default:
				loginServiceName = "Logged out";
				break;
		}

		loginServiceEditText.setText(loginServiceName);

		String uid;
		UserProfileManager.UserProfile currentProfile = UserProfileManager.getInstance().getCurrentUser();
		if (currentProfile != null && currentProfile.UID != null) {
			uid = currentProfile.UID;
		} else {
			uid = "<unknown>";
		}

		uidEditText.setText(uid);
	}

	public void showLogin() {
		startActivity(new Intent(this, LoginActivity.class));
	}
}
