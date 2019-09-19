package com.enjcat.todolist

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import io.realm.Realm
import io.realm.kotlin.createObject
import io.realm.kotlin.where
import kotlinx.android.synthetic.main.activity_edit.*
import kotlinx.android.synthetic.main.activity_main.*
import org.jetbrains.anko.alert
import org.jetbrains.anko.yesButton
import java.util.*

class EditActivity : AppCompatActivity() {
    val realm = Realm.getDefaultInstance()
    val calendar : Calendar = Calendar.getInstance()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_edit)
        val id = intent.getLongExtra("id", -1L)
        if (id == -1L){
            insertMode()
        }else{
            updateMode(id)
        }

        calendarView.setOnDateChangeListener { view, year, month, dayOfMonth ->
            calendar.set(Calendar.YEAR, year)
            calendar.set(Calendar.MONTH, month)
            calendar.set(Calendar.DAY_OF_MONTH, dayOfMonth)
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        realm.close()
    }

    private fun insertTodo(){
        realm.beginTransaction()
        val todo = realm.createObject<Todo>(nextId())
        todo.title = TodoeditText.text.toString()
        todo.date = calendar.timeInMillis
        realm.commitTransaction()

        alert ( "내용이 추가되었습니다." ){yesButton { finish() }}.show()
    }

    private  fun nextId(): Int{
        val maxId = realm.where<Todo>().max("id")
        if(maxId != null){
            return maxId.toInt() + 1
        }
        return 0
    }

    private fun UpdateTodo(id : Long){
        realm.beginTransaction()
        val todo = realm.where<Todo>().equalTo("id", id).findFirst()!!
        todo.title = TodoeditText.text.toString()
        todo.date = calendar.timeInMillis
        realm.commitTransaction()

        alert ( "내용이 변경되었습니다." ){yesButton { finish() }}.show()
    }

    private fun deleteTodo(id : Long){
        realm.beginTransaction()
        val todo = realm.where<Todo>().equalTo("id", id).findFirst()!!
        todo.deleteFromRealm()
        realm.commitTransaction()

        alert ( "내용이 삭제되었습니다." ){yesButton { finish() }}.show()
    }

    @SuppressLint("RestrictedApi")
    private fun insertMode(){
        deleteFab.visibility = View.GONE
        doneFab.setOnClickListener{
            insertTodo()
        }
    }

    private fun updateMode(id: Long){
        val todo = realm.where<Todo>().equalTo("id", id).findFirst()!!
        TodoeditText.setText(todo.title)
        calendarView.date = todo.date

        doneFab.setOnClickListener{
            UpdateTodo(id)
        }
        deleteFab.setOnClickListener {
            deleteTodo(id)
        }
    }
}
