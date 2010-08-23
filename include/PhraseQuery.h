/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2010 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Query.h"
#include "Weight.h"

namespace Lucene
{
	/// A Query that matches documents containing a particular sequence of terms.  A PhraseQuery is built by 
	/// QueryParser for input like "new york".
	///
	/// This query may be combined with other terms or queries with a {@link BooleanQuery}.
	class LPPAPI PhraseQuery : public Query
	{
	public:
		/// Constructs an empty phrase query.
		PhraseQuery();
		virtual ~PhraseQuery();
	
		LUCENE_CLASS(PhraseQuery);
	
	protected:
		String field;
		Collection<TermPtr> terms;
		Collection<int32_t> positions;
		int32_t maxPosition;
		int32_t slop;
	
	public:
		using Query::toString;
		
		/// Sets the number of other words permitted between words in query phrase.  If zero, then this is an 
		/// exact phrase search.  For larger values this works like a WITHIN or NEAR operator.
		///
		/// The slop is in fact an edit-distance, where the units correspond to moves of terms in the query phrase 
		/// out of position.  For example, to switch the order of two words requires two moves (the first move 
		/// places the words atop one another), so to permit re-orderings of phrases, the slop must be at least two.
		///
		/// More exact matches are scored higher than sloppier matches, thus search results are sorted by exactness.
		///
		/// The slop is zero by default, requiring exact matches.
		void setSlop(int32_t slop);
		
		/// Returns the slop.
		/// @see #setSlop()
		int32_t getSlop();
		
		/// Adds a term to the end of the query phrase.
		/// The relative position of the term is the one immediately after the last term added.
		void add(TermPtr term);
		
		/// Adds a term to the end of the query phrase.
		/// The relative position of the term within the phrase is specified explicitly.  This allows eg. phrases 
		/// with more than one term at the same position or phrases with gaps (eg. in connection with stopwords).
		void add(TermPtr term, int32_t position);
		
		/// Returns the set of terms in this phrase.
		Collection<TermPtr> getTerms();
		
		/// Returns the relative positions of terms in this phrase.
		Collection<int32_t> getPositions();
		
		virtual WeightPtr createWeight(SearcherPtr searcher);
		virtual void extractTerms(SetTerm terms);
		
		/// Prints a user-readable version of this query.
		virtual String toString(const String& field);
		
		virtual bool equals(LuceneObjectPtr other);
		virtual int32_t hashCode();
		virtual LuceneObjectPtr clone(LuceneObjectPtr other = LuceneObjectPtr());
		
		friend class PhraseWeight;
	};
	
	class LPPAPI PhraseWeight : public Weight
	{
	public:
		PhraseWeight(PhraseQueryPtr query, SearcherPtr searcher);
		virtual ~PhraseWeight();
	
		LUCENE_CLASS(PhraseWeight);
	
	protected:
		PhraseQueryPtr query;
		SimilarityPtr similarity;
		double value;
		double idf;
		double queryNorm;
		double queryWeight;
		IDFExplanationPtr idfExp;
	
	public:
		virtual String toString();
		virtual QueryPtr getQuery();
		virtual double getValue();
		virtual double sumOfSquaredWeights();
		virtual void normalize(double norm);
		virtual ScorerPtr scorer(IndexReaderPtr reader, bool scoreDocsInOrder, bool topScorer);
		virtual ExplanationPtr explain(IndexReaderPtr reader, int32_t doc);
	};
}