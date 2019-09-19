package com.enjcat.todolist

import android.text.format.DateFormat
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import io.realm.OrderedRealmCollection
import io.realm.RealmBaseAdapter
import kotlinx.android.synthetic.main.item_todo.view.*
import java.util.zip.DataFormatException

class TodoListAdapter (realmResult : OrderedRealmCollection<Todo>) : RealmBaseAdapter<Todo>(realmResult){
    override fun getView(position: Int, convertView: View?, parent: ViewGroup?): View {
        val vh: ViewHolder
        val view: View

        if (convertView == null){
            view = LayoutInflater.from(parent?.context).inflate(R.layout.item_todo, parent, false)

            vh = ViewHolder(view)
            view.tag = vh
        }else{
            view = convertView
            vh = view.tag as ViewHolder
        }
        if (adapterData != null){
            val item = adapterData!![position]
            vh.textTextView.text = "${item.title} / position : ${position} / id : ${item.id}"
            vh.dateTextView.text = DateFormat.format("MM/dd", item.date)
        }
        return view
    }

    override fun getItemId(position: Int): Long {
        if (adapterData != null){
            return adapterData!![position].id
        }
        return super.getItemId(position)
    }

    class ViewHolder(view : View){
        val dateTextView: TextView = view.findViewById(R.id.dateTextView)
        val textTextView: TextView = view.findViewById(R.id.textTextView)
    }
}