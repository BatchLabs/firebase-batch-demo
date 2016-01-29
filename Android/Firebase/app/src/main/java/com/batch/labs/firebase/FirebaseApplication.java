package com.batch.labs.firebase;

import android.app.Application;
import android.support.v4.content.ContextCompat;

import com.batch.android.Batch;
import com.batch.android.Config;
import com.firebase.client.Firebase;
import com.squareup.otto.Bus;

public class FirebaseApplication extends Application
{
	private static FirebaseApplication instance;

	public static FirebaseApplication getInstance() {
		return instance;
	}

	public static Bus getEventBus() {
		return instance.eventBus;
	}

	private Bus eventBus;

	@Override
	public void onCreate()
	{
		super.onCreate();

		instance = this;

		eventBus = new Bus();

		Firebase.setAndroidContext(this);

		Batch.setConfig(new Config(com.batch.labs.firebase.Config.BATCH_API_KEY));
		Batch.Push.setGCMSenderId(com.batch.labs.firebase.Config.GCM_SENDER_ID);
		Batch.Push.setNotificationsColor(ContextCompat.getColor(this, R.color.colorPrimary));
		Batch.Push.setSmallIconResourceId(R.drawable.ic_notification);

		if (UserProfileManager.getInstance().getCurrentLoginType() != UserProfileManager.LoginType.LOGGED_OUT) {
			UserProfileManager.getInstance().readAuthInfo();
		}
	}
}
