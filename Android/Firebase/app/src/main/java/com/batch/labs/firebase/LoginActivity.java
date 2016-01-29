package com.batch.labs.firebase;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.util.Log;
import android.view.View;

import com.batch.labs.firebase.events.UserLoggedInEvent;
import com.batch.labs.firebase.events.UserLoginFailedEvent;
import com.google.android.gms.auth.GoogleAuthException;
import com.google.android.gms.auth.GoogleAuthUtil;
import com.google.android.gms.auth.UserRecoverableAuthException;
import com.google.android.gms.auth.api.Auth;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.auth.api.signin.GoogleSignInResult;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.Scopes;
import com.google.android.gms.common.api.GoogleApiClient;
import com.squareup.otto.Subscribe;

import java.io.IOException;

public class LoginActivity extends BaseActivity
{
	private static final String TAG = "LoginActivity";
	private static final int RC_SIGN_IN = 9001;
	private static final int RC_GOOGLE_LOGIN = 9002;

	private GoogleApiClient googleApiClient;
	private boolean googleSigninRetried = false;

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_login);

		findViewById(R.id.google_sign_in_button).setOnClickListener(new View.OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				doGoogleSignin();
			}
		});

		findViewById(R.id.anonymous_sign_in_button).setOnClickListener(new View.OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				UserProfileManager.getInstance().loginAnonymously();
			}
		});

		// Google Sign-In setup
		GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
				.requestId()
				.requestEmail()
				.requestProfile()
				.build();

		googleApiClient = new GoogleApiClient.Builder(this)
				.enableAutoManage(this, new GoogleApiClient.OnConnectionFailedListener()
				{
					@Override
					public void onConnectionFailed(ConnectionResult connectionResult)
					{
						Log.e(TAG, "GoogleApiClient connection failed:" + connectionResult.getErrorMessage());
					}
				})
				.addApi(Auth.GOOGLE_SIGN_IN_API, gso)
				.build();
	}

	@Override
	protected void onStart()
	{
		super.onStart();

		if (UserProfileManager.getInstance().getCurrentLoginType() == UserProfileManager.LoginType.GOOGLE) {
			doGoogleSignin();
		}
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data)
	{
		super.onActivityResult(requestCode, resultCode, data);

		if (requestCode == RC_SIGN_IN) {
			GoogleSignInResult result = Auth.GoogleSignInApi.getSignInResultFromIntent(data);
			handleSignInResult(result);
		} else if (requestCode == RC_GOOGLE_LOGIN) {
			// Try to sign in one more time before erroring
			if (!googleSigninRetried) {
				doGoogleSignin();
				googleSigninRetried = true;
			} else {
				// Avoid an infinite loop
				googleSigninRetried = false;
				FirebaseApplication.getEventBus().post(new UserLoginFailedEvent());
			}
		}
	}

	private void handleSignInResult(final GoogleSignInResult result) {
		if (result.isSuccess()) {
			new Thread(new Runnable()
			{
				@Override
				public void run()
				{
					try
					{
						String token = GoogleAuthUtil.getToken(LoginActivity.this, result.getSignInAccount().getEmail(), String.format("oauth2:%s", Scopes.PLUS_LOGIN));
						if (token == null) {
							Log.e(TAG, "Null GoogleAuthUtil token. Aborting.");
							FirebaseApplication.getEventBus().post(new UserLoginFailedEvent());
							return;
						}
						UserProfileManager.getInstance().loginWithGoogle(token, result.getSignInAccount());
					}
					catch (UserRecoverableAuthException e)
					{
						Log.w(TAG, "Recoverable Google OAuth error: " + e.toString());
						Intent recover = e.getIntent();
						startActivityForResult(recover, RC_GOOGLE_LOGIN);
					}
					catch (IOException |GoogleAuthException e)
					{
						e.printStackTrace();
						FirebaseApplication.getEventBus().post(new UserLoginFailedEvent());
					}
				}
			}).start();
		} else {
			FirebaseApplication.getEventBus().post(new UserLoginFailedEvent());
		}
	}

	public void doGoogleSignin() {
		Intent signInIntent = Auth.GoogleSignInApi.getSignInIntent(googleApiClient);
		startActivityForResult(signInIntent, RC_SIGN_IN);
	}

	// -------- Events -----------

	@Subscribe
	@SuppressWarnings("unused")
	public void userLoggedIn(UserLoggedInEvent event) {
		finish();
	}

	@Subscribe
	@SuppressWarnings("unused")
	public void userLoginFailed(UserLoginFailedEvent event) {
		new AlertDialog.Builder(this)
				.setTitle(getString(R.string.login_error_title))
				.setMessage(getString(R.string.login_error_message))
				.setNegativeButton(getString(R.string.ok), null)
				.setCancelable(true)
				.show();
	}
}
