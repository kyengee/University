package com.enjcat.todolist

import android.app.Application
import io.realm.Realm

class MyApplycation : Application(){
    override fun onCreate() {
        super.onCreate()
        Realm.init(this)
    }
}