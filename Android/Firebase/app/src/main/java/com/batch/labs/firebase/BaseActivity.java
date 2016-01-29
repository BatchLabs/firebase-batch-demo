package com.batch.labs.firebase;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import com.batch.android.Batch;

public class BaseActivity extends AppCompatActivity
{

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		setTitle(R.string.activity_title);

		FirebaseApplication.getEventBus().register(this);
	}

	@Override
	protected void onStart()
	{
		super.onStart();
		Batch.onStart(this);
	}

	@Override
	protected void onStop()
	{
		Batch.onStop(this);
		super.onStop();
	}

	@Override
	protected void onDestroy()
	{
		Batch.onDestroy(this);
		FirebaseApplication.getEventBus().unregister(this);
		super.onDestroy();
	}

	@Override
	protected void onNewIntent(Intent intent)
	{
		super.onNewIntent(intent);
		Batch.onNewIntent(this, intent);
	}
}
